---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 05:01:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 11 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (5 unique values: 36-46 cores)</summary>

```
1789721681 36
1789721686 36
1789721691 41
1789721696 41
1789721701 41
1789721706 41
1789721711 41
1789721716 41
1789721721 46
1789721726 46
1789721731 46
1789721736 46
1789721741 46
1789721746 44
1789721751 44
1789721756 44
1789721761 44
1789721766 44
1789721771 44
1789721776 39
```
</details>

---

