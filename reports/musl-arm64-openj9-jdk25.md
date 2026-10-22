---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-22 12:40:51 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 9 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1792686933 32
1792686938 32
1792686943 32
1792686948 32
1792686953 32
1792686958 32
1792686963 32
1792686968 32
1792686973 32
1792686978 32
1792686983 32
1792686988 32
1792686993 32
1792686998 32
1792687003 32
1792687008 32
1792687013 32
1792687018 32
1792687023 32
1792687028 32
```
</details>

---

