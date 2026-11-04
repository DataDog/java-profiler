---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-04 12:28:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 12 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 11 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (1 unique values: 51-51 cores)</summary>

```
1793812839 51
1793812844 51
1793812849 51
1793812854 51
1793812859 51
1793812864 51
1793812869 51
1793812874 51
1793812879 51
1793812884 51
1793812889 51
1793812894 51
1793812899 51
1793812904 51
1793812909 51
1793812914 51
1793812919 51
1793812924 51
1793812929 51
1793812934 51
```
</details>

---

