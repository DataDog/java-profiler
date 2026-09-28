---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-28 06:45:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 603 |
| Sample Rate | 10.05/sec |
| Health Score | 628% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 763 |
| Sample Rate | 12.72/sec |
| Health Score | 795% |
| Threads | 10 |
| Allocations | 544 |

<details>
<summary>CPU Timeline (3 unique values: 55-59 cores)</summary>

```
1790592070 55
1790592075 55
1790592080 55
1790592085 57
1790592090 57
1790592095 57
1790592100 57
1790592105 57
1790592110 59
1790592115 59
1790592120 59
1790592125 59
1790592130 59
1790592135 59
1790592140 59
1790592145 59
1790592150 59
1790592155 59
1790592160 59
1790592165 59
```
</details>

---

