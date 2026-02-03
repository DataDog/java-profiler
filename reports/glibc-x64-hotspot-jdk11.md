---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-03 12:32:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 8 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (2 unique values: 29-32 cores)</summary>

```
1770139658 32
1770139663 32
1770139668 32
1770139673 32
1770139678 32
1770139683 32
1770139688 32
1770139693 32
1770139698 32
1770139703 32
1770139708 32
1770139713 32
1770139718 32
1770139723 32
1770139728 32
1770139733 32
1770139738 32
1770139743 32
1770139748 29
1770139753 29
```
</details>

---

