---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-21 07:16:24 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 10 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 255 |
| Sample Rate | 4.25/sec |
| Health Score | 266% |
| Threads | 11 |
| Allocations | 132 |

<details>
<summary>CPU Timeline (2 unique values: 28-48 cores)</summary>

```
1792581002 48
1792581007 48
1792581012 48
1792581017 48
1792581023 48
1792581028 48
1792581033 48
1792581038 48
1792581043 48
1792581048 48
1792581053 48
1792581058 48
1792581063 48
1792581068 48
1792581073 48
1792581078 48
1792581083 48
1792581088 48
1792581093 48
1792581098 48
```
</details>

---

