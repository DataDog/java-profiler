---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-29 10:08:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 11 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 28 |
| Sample Rate | 0.47/sec |
| Health Score | 29% |
| Threads | 10 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790690671 43
1790690676 43
1790690681 43
1790690686 43
1790690691 43
1790690696 43
1790690701 43
1790690706 43
1790690711 43
1790690716 43
1790690721 43
1790690726 43
1790690731 43
1790690736 43
1790690741 43
1790690746 43
1790690751 48
1790690756 48
1790690761 48
1790690766 48
```
</details>

---

