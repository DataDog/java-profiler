---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-30 17:09:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 11 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 218 |
| Sample Rate | 3.63/sec |
| Health Score | 227% |
| Threads | 13 |
| Allocations | 137 |

<details>
<summary>CPU Timeline (2 unique values: 43-45 cores)</summary>

```
1793394261 43
1793394266 43
1793394271 43
1793394276 43
1793394281 43
1793394286 43
1793394291 43
1793394296 43
1793394301 43
1793394306 43
1793394311 43
1793394316 43
1793394321 43
1793394326 43
1793394331 43
1793394336 43
1793394341 43
1793394346 43
1793394351 43
1793394356 43
```
</details>

---

