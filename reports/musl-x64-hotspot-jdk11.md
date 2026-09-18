---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 05:01:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 8 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 855 |
| Sample Rate | 14.25/sec |
| Health Score | 891% |
| Threads | 10 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (5 unique values: 25-50 cores)</summary>

```
1789721695 41
1789721700 41
1789721705 41
1789721710 29
1789721715 29
1789721720 29
1789721725 29
1789721730 29
1789721735 29
1789721740 29
1789721745 29
1789721750 27
1789721755 27
1789721760 25
1789721765 25
1789721770 25
1789721775 25
1789721780 25
1789721785 25
1789721790 25
```
</details>

---

