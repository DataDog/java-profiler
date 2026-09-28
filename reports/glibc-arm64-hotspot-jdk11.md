---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-28 06:45:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 10 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (2 unique values: 41-43 cores)</summary>

```
1790592065 43
1790592070 43
1790592075 43
1790592080 43
1790592085 43
1790592090 43
1790592095 43
1790592100 43
1790592105 43
1790592110 41
1790592115 41
1790592120 41
1790592125 41
1790592130 41
1790592135 41
1790592140 41
1790592145 41
1790592150 41
1790592155 41
1790592160 41
```
</details>

---

