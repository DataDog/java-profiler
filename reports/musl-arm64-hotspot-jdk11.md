---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-20 01:06:53 EDT

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 7 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 13 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (3 unique values: 23-48 cores)</summary>

```
1792472527 23
1792472532 23
1792472537 23
1792472542 23
1792472547 23
1792472552 23
1792472557 23
1792472562 23
1792472567 23
1792472572 23
1792472577 23
1792472582 23
1792472587 43
1792472592 43
1792472597 43
1792472602 43
1792472607 43
1792472612 43
1792472617 43
1792472622 43
```
</details>

---

