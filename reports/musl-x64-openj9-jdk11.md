---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-21 10:08:18 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 680 |
| Sample Rate | 11.33/sec |
| Health Score | 708% |
| Threads | 9 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (2 unique values: 49-96 cores)</summary>

```
1787321107 49
1787321112 49
1787321117 49
1787321122 49
1787321127 49
1787321132 49
1787321137 49
1787321142 96
1787321147 96
1787321152 96
1787321157 96
1787321162 96
1787321167 96
1787321172 96
1787321177 96
1787321182 96
1787321187 96
1787321192 96
1787321197 96
1787321202 96
```
</details>

---

