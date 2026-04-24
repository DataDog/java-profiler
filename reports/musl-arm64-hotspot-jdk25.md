---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-24 12:55:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 314 |
| Sample Rate | 5.23/sec |
| Health Score | 327% |
| Threads | 14 |
| Allocations | 152 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777049476 64
1777049481 64
1777049486 64
1777049491 64
1777049496 64
1777049501 64
1777049506 64
1777049511 64
1777049516 64
1777049521 64
1777049526 64
1777049532 64
1777049537 64
1777049542 64
1777049547 64
1777049552 64
1777049557 64
1777049562 64
1777049567 64
1777049572 64
```
</details>

---

