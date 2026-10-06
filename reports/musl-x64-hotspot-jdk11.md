---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-06 05:52:40 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 797 |
| Sample Rate | 13.28/sec |
| Health Score | 830% |
| Threads | 10 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1791279937 32
1791279942 32
1791279947 32
1791279952 32
1791279957 32
1791279962 32
1791279967 32
1791279972 32
1791279977 32
1791279982 32
1791279987 32
1791279992 32
1791279997 32
1791280002 32
1791280007 32
1791280012 32
1791280017 32
1791280022 32
1791280027 32
1791280032 32
```
</details>

---

