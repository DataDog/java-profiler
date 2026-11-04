---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-04 18:30:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 168 |
| Sample Rate | 2.80/sec |
| Health Score | 175% |
| Threads | 9 |
| Allocations | 164 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 11 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1793834752 32
1793834757 32
1793834762 32
1793834767 32
1793834772 32
1793834777 32
1793834782 32
1793834787 32
1793834792 32
1793834797 32
1793834802 32
1793834807 32
1793834812 32
1793834817 32
1793834822 32
1793834827 32
1793834832 32
1793834837 32
1793834842 32
1793834847 32
```
</details>

---

