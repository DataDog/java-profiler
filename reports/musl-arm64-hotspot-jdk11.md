---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-02 07:03:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 10 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (2 unique values: 31-44 cores)</summary>

```
1793620779 44
1793620784 44
1793620789 31
1793620794 31
1793620799 31
1793620804 31
1793620809 31
1793620814 31
1793620819 31
1793620824 31
1793620829 31
1793620834 31
1793620839 31
1793620844 31
1793620849 31
1793620854 31
1793620859 31
1793620864 31
1793620869 31
1793620874 31
```
</details>

---

