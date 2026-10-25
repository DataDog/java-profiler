---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-25 08:54:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 446 |
| Sample Rate | 7.43/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 9.52/sec |
| Health Score | 595% |
| Threads | 10 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (3 unique values: 13-63 cores)</summary>

```
1792932503 13
1792932508 13
1792932513 13
1792932518 13
1792932523 13
1792932528 13
1792932533 13
1792932538 13
1792932543 13
1792932548 13
1792932553 13
1792932558 13
1792932563 13
1792932568 13
1792932573 30
1792932578 30
1792932583 30
1792932588 30
1792932593 63
1792932598 63
```
</details>

---

