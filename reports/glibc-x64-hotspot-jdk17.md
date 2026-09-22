---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-22 07:06:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 630 |
| Sample Rate | 10.50/sec |
| Health Score | 656% |
| Threads | 10 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (3 unique values: 44-72 cores)</summary>

```
1790074843 62
1790074848 62
1790074853 62
1790074858 62
1790074863 62
1790074868 62
1790074873 62
1790074878 62
1790074883 62
1790074888 62
1790074893 62
1790074898 62
1790074903 62
1790074908 62
1790074913 62
1790074918 72
1790074923 72
1790074928 72
1790074933 72
1790074938 72
```
</details>

---

