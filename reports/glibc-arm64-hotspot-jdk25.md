---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-13 07:44:36 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 395 |
| Sample Rate | 6.58/sec |
| Health Score | 411% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 8 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (5 unique values: 40-46 cores)</summary>

```
1791891567 40
1791891572 40
1791891577 40
1791891582 40
1791891587 40
1791891592 40
1791891597 40
1791891602 40
1791891607 40
1791891612 40
1791891617 42
1791891622 42
1791891627 44
1791891632 44
1791891637 44
1791891642 46
1791891647 46
1791891652 46
1791891657 46
1791891662 46
```
</details>

---

