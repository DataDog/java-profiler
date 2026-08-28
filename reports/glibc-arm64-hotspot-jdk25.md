---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-28 08:25:44 EDT

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1787919686 29
1787919691 29
1787919696 29
1787919701 29
1787919706 29
1787919711 29
1787919716 34
1787919721 34
1787919726 29
1787919731 29
1787919736 29
1787919741 29
1787919746 29
1787919751 29
1787919756 29
1787919761 29
1787919766 29
1787919771 29
1787919776 29
1787919781 34
```
</details>

---

