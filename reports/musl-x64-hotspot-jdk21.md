---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-06 04:52:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 10 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (3 unique values: 27-70 cores)</summary>

```
1786006053 27
1786006058 27
1786006063 27
1786006068 27
1786006073 27
1786006078 27
1786006083 62
1786006088 62
1786006093 62
1786006098 62
1786006103 62
1786006108 62
1786006113 62
1786006118 62
1786006123 62
1786006128 62
1786006133 62
1786006138 70
1786006143 70
1786006148 70
```
</details>

---

