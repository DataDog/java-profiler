---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-05 12:01:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 12 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793897767 48
1793897772 48
1793897777 48
1793897782 48
1793897787 48
1793897792 48
1793897797 48
1793897802 48
1793897807 48
1793897812 48
1793897817 48
1793897822 48
1793897827 48
1793897832 48
1793897837 48
1793897842 48
1793897847 48
1793897852 48
1793897857 48
1793897862 48
```
</details>

---

