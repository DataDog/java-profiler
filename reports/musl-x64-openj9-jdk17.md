---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ❌ FAIL

**Date:** 2026-09-21 17:43:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 72-72 cores)</summary>

```
1790026676 72
1790026681 72
1790026686 72
1790026691 72
1790026696 72
1790026701 72
1790026706 72
1790026711 72
1790026716 72
1790026721 72
1790026726 72
1790026731 72
1790026736 72
1790026741 72
1790026746 72
1790026751 72
1790026756 72
1790026761 72
1790026766 72
1790026771 72
```
</details>

---

