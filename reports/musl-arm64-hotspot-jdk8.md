---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-13 07:44:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 12 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1791891567 51
1791891572 51
1791891577 51
1791891582 51
1791891587 46
1791891592 46
1791891597 46
1791891602 46
1791891607 46
1791891612 46
1791891617 46
1791891622 46
1791891627 46
1791891632 46
1791891637 46
1791891642 46
1791891647 46
1791891652 46
1791891657 46
1791891662 46
```
</details>

---

