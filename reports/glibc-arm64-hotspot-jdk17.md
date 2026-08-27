---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-27 09:40:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 316 |
| Sample Rate | 5.27/sec |
| Health Score | 329% |
| Threads | 12 |
| Allocations | 156 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 150 |
| Sample Rate | 2.50/sec |
| Health Score | 156% |
| Threads | 11 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1787837788 43
1787837793 43
1787837798 43
1787837803 43
1787837808 43
1787837813 43
1787837818 38
1787837823 38
1787837828 38
1787837833 38
1787837838 38
1787837843 38
1787837848 38
1787837853 38
1787837858 38
1787837863 38
1787837868 38
1787837873 38
1787837878 43
1787837883 43
```
</details>

---

