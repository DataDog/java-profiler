---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-04 12:28:12 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 591 |
| Sample Rate | 9.85/sec |
| Health Score | 616% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 851 |
| Sample Rate | 14.18/sec |
| Health Score | 886% |
| Threads | 9 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1793812837 49
1793812842 49
1793812847 49
1793812852 49
1793812857 49
1793812862 49
1793812867 49
1793812872 49
1793812877 49
1793812882 49
1793812887 49
1793812892 49
1793812897 49
1793812902 49
1793812907 49
1793812912 49
1793812917 49
1793812922 49
1793812927 49
1793812932 51
```
</details>

---

