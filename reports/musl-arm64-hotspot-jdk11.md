---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-18 08:24:28 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 7 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 401 |
| Sample Rate | 6.68/sec |
| Health Score | 418% |
| Threads | 14 |
| Allocations | 144 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787055552 43
1787055557 43
1787055562 43
1787055567 43
1787055572 43
1787055577 43
1787055582 48
1787055587 48
1787055592 48
1787055597 48
1787055602 48
1787055607 48
1787055612 48
1787055617 48
1787055622 48
1787055627 48
1787055632 48
1787055637 48
1787055642 48
1787055647 48
```
</details>

---

