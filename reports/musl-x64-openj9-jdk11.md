---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-04 10:55:48 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 851 |
| Sample Rate | 14.18/sec |
| Health Score | 886% |
| Threads | 10 |
| Allocations | 548 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1770220130 32
1770220135 32
1770220140 32
1770220145 32
1770220150 32
1770220155 32
1770220160 32
1770220165 32
1770220170 32
1770220175 32
1770220180 32
1770220185 32
1770220190 30
1770220195 30
1770220200 32
1770220205 32
1770220210 32
1770220215 32
1770220220 32
1770220225 32
```
</details>

---

