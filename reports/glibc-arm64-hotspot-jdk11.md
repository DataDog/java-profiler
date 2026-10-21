---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-21 07:16:21 EDT

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
| CPU Cores (start) | 9 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 214 |
| Sample Rate | 3.57/sec |
| Health Score | 223% |
| Threads | 13 |
| Allocations | 79 |

<details>
<summary>CPU Timeline (3 unique values: 9-44 cores)</summary>

```
1792581020 9
1792581025 9
1792581030 9
1792581035 9
1792581040 9
1792581045 9
1792581050 9
1792581055 9
1792581060 44
1792581065 44
1792581070 44
1792581075 44
1792581080 44
1792581085 44
1792581090 44
1792581095 44
1792581100 44
1792581105 44
1792581110 44
1792581115 44
```
</details>

---

