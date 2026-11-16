---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-16 09:37:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 12 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (2 unique values: 38-48 cores)</summary>

```
1794839610 48
1794839615 48
1794839620 48
1794839625 48
1794839630 48
1794839635 48
1794839640 48
1794839645 48
1794839650 48
1794839655 48
1794839660 48
1794839665 48
1794839670 48
1794839675 48
1794839680 48
1794839686 38
1794839691 38
1794839696 38
1794839701 38
1794839706 38
```
</details>

---

