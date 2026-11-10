---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-10 08:53:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 228 |
| Sample Rate | 3.80/sec |
| Health Score | 237% |
| Threads | 8 |
| Allocations | 163 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 242 |
| Sample Rate | 4.03/sec |
| Health Score | 252% |
| Threads | 14 |
| Allocations | 114 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1794318466 43
1794318471 43
1794318476 43
1794318481 48
1794318486 48
1794318491 48
1794318496 48
1794318501 48
1794318506 48
1794318511 48
1794318516 48
1794318521 48
1794318526 48
1794318531 48
1794318536 48
1794318541 48
1794318546 48
1794318551 48
1794318556 48
1794318561 48
```
</details>

---

