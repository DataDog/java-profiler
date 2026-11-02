---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-02 07:03:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 12 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (1 unique values: 30-30 cores)</summary>

```
1793620783 30
1793620789 30
1793620794 30
1793620799 30
1793620804 30
1793620809 30
1793620814 30
1793620819 30
1793620824 30
1793620829 30
1793620834 30
1793620839 30
1793620844 30
1793620849 30
1793620854 30
1793620859 30
1793620864 30
1793620869 30
1793620874 30
1793620879 30
```
</details>

---

