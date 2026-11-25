---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-25 13:36:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 173 |
| Sample Rate | 2.88/sec |
| Health Score | 180% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 411 |
| Sample Rate | 6.85/sec |
| Health Score | 428% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (7 unique values: 54-78 cores)</summary>

```
1795631441 54
1795631446 54
1795631451 54
1795631456 54
1795631461 54
1795631466 63
1795631471 63
1795631476 63
1795631481 68
1795631486 68
1795631491 65
1795631496 65
1795631501 74
1795631506 74
1795631511 74
1795631516 74
1795631521 74
1795631526 74
1795631531 74
1795631536 76
```
</details>

---

