---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-21 08:20:54 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (4 unique values: 48-54 cores)</summary>

```
1792584986 49
1792584991 49
1792584996 49
1792585001 54
1792585006 54
1792585011 54
1792585016 54
1792585021 49
1792585026 49
1792585031 49
1792585036 48
1792585041 48
1792585046 48
1792585051 48
1792585056 48
1792585061 48
1792585066 48
1792585071 48
1792585076 48
1792585081 48
```
</details>

---

