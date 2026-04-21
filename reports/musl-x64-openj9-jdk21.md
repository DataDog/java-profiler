---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-21 14:31:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 761 |
| Sample Rate | 12.68/sec |
| Health Score | 792% |
| Threads | 11 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (4 unique values: 89-96 cores)</summary>

```
1776796090 96
1776796095 96
1776796100 96
1776796105 96
1776796110 96
1776796115 96
1776796120 96
1776796125 96
1776796130 96
1776796135 96
1776796140 96
1776796145 96
1776796150 91
1776796155 91
1776796160 89
1776796165 89
1776796170 89
1776796175 94
1776796180 94
1776796185 94
```
</details>

---

