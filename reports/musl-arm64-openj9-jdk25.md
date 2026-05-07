---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-07 12:39:48 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 765 |
| Sample Rate | 12.75/sec |
| Health Score | 797% |
| Threads | 11 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1778171727 64
1778171732 64
1778171737 64
1778171742 64
1778171747 64
1778171752 64
1778171757 64
1778171762 64
1778171767 64
1778171772 64
1778171777 64
1778171782 64
1778171787 64
1778171792 64
1778171797 64
1778171802 64
1778171807 64
1778171812 64
1778171817 64
1778171822 64
```
</details>

---

