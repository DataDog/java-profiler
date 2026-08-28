---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-28 08:25:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 10 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (4 unique values: 38-48 cores)</summary>

```
1787919676 45
1787919681 45
1787919686 48
1787919691 48
1787919696 48
1787919701 48
1787919706 43
1787919711 43
1787919716 43
1787919721 43
1787919726 43
1787919731 43
1787919736 43
1787919741 43
1787919746 43
1787919751 43
1787919756 43
1787919761 43
1787919766 43
1787919771 43
```
</details>

---

