---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-13 07:44:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 443 |
| Sample Rate | 7.38/sec |
| Health Score | 461% |
| Threads | 8 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 786 |
| Sample Rate | 13.10/sec |
| Health Score | 819% |
| Threads | 11 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1791891532 30
1791891537 30
1791891542 30
1791891547 30
1791891552 30
1791891557 30
1791891562 30
1791891567 32
1791891572 32
1791891577 32
1791891582 32
1791891587 32
1791891592 32
1791891597 32
1791891602 32
1791891607 32
1791891612 32
1791891617 32
1791891622 32
1791891627 32
```
</details>

---

