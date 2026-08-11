---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-11 09:44:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
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
| CPU Samples | 448 |
| Sample Rate | 7.47/sec |
| Health Score | 467% |
| Threads | 8 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 9 |
| Sample Rate | 0.15/sec |
| Health Score | 9% |
| Threads | 6 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (4 unique values: 25-32 cores)</summary>

```
1786455545 32
1786455550 32
1786455555 31
1786455560 31
1786455565 31
1786455570 31
1786455575 31
1786455580 31
1786455585 30
1786455590 30
1786455595 30
1786455600 25
1786455605 25
1786455610 25
1786455615 25
1786455620 25
1786455625 25
1786455630 25
1786455635 25
1786455640 25
```
</details>

---

