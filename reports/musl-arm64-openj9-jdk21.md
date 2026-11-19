---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 06:06:31 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 265 |
| Sample Rate | 4.42/sec |
| Health Score | 276% |
| Threads | 10 |
| Allocations | 144 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 301 |
| Sample Rate | 5.02/sec |
| Health Score | 314% |
| Threads | 12 |
| Allocations | 168 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795085923 50
1795085928 50
1795085933 50
1795085938 50
1795085943 50
1795085948 50
1795085953 50
1795085958 50
1795085963 50
1795085968 50
1795085973 50
1795085978 50
1795085983 50
1795085988 50
1795085993 50
1795085998 50
1795086003 50
1795086008 50
1795086013 50
1795086018 50
```
</details>

---

