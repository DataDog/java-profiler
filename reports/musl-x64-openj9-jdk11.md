---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-10 01:04:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 737 |
| Sample Rate | 12.28/sec |
| Health Score | 767% |
| Threads | 10 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (4 unique values: 62-96 cores)</summary>

```
1786337933 96
1786337938 96
1786337943 94
1786337948 94
1786337953 92
1786337958 92
1786337963 92
1786337968 92
1786337973 92
1786337978 92
1786337983 92
1786337988 92
1786337993 92
1786337998 92
1786338003 92
1786338008 92
1786338013 92
1786338018 92
1786338023 92
1786338028 92
```
</details>

---

