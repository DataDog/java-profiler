---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-02-03 08:18:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 151 |
| Sample Rate | 2.52/sec |
| Health Score | 158% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 176 |
| Sample Rate | 2.93/sec |
| Health Score | 183% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 40-42 cores)</summary>

```
1770119095 42
1770119100 42
1770119105 42
1770119110 42
1770119115 42
1770119120 42
1770119125 42
1770119130 42
1770119135 42
1770119140 42
1770119145 42
1770119150 42
1770119155 42
1770119160 42
1770119165 42
1770119170 42
1770119175 42
1770119180 42
1770119185 40
1770119190 40
```
</details>

---

