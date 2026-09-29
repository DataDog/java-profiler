---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-29 11:52:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 686 |
| Sample Rate | 11.43/sec |
| Health Score | 714% |
| Threads | 11 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (3 unique values: 37-56 cores)</summary>

```
1790696792 46
1790696797 46
1790696802 46
1790696807 46
1790696812 46
1790696817 46
1790696822 37
1790696827 37
1790696832 37
1790696837 37
1790696842 37
1790696847 37
1790696852 37
1790696857 37
1790696862 56
1790696867 56
1790696872 56
1790696878 56
1790696883 56
1790696888 56
```
</details>

---

