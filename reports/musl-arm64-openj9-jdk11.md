---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 12:40:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 10 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 12 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (2 unique values: 34-37 cores)</summary>

```
1792686983 34
1792686988 34
1792686993 34
1792686998 34
1792687003 34
1792687008 34
1792687013 34
1792687018 34
1792687023 37
1792687028 37
1792687033 37
1792687038 37
1792687043 37
1792687048 37
1792687053 37
1792687058 37
1792687063 37
1792687069 37
1792687074 37
1792687079 37
```
</details>

---

