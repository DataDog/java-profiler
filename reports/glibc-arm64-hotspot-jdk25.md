---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-30 00:57:21 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 11 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 262 |
| Sample Rate | 4.37/sec |
| Health Score | 273% |
| Threads | 13 |
| Allocations | 125 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1788065651 34
1788065656 34
1788065661 34
1788065666 34
1788065671 34
1788065676 34
1788065681 34
1788065686 34
1788065691 34
1788065696 34
1788065701 34
1788065706 34
1788065711 29
1788065716 29
1788065721 29
1788065726 29
1788065731 29
1788065736 29
1788065741 29
1788065746 29
```
</details>

---

