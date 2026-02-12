---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-12 07:47:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 9 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 688 |
| Sample Rate | 11.47/sec |
| Health Score | 717% |
| Threads | 10 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 787 |
| Sample Rate | 13.12/sec |
| Health Score | 820% |
| Threads | 12 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (2 unique values: 9-13 cores)</summary>

```
1770900097 9
1770900102 9
1770900107 9
1770900112 9
1770900117 9
1770900122 9
1770900127 9
1770900132 9
1770900137 9
1770900142 9
1770900147 9
1770900152 9
1770900157 13
1770900162 13
1770900167 13
1770900172 13
1770900177 13
1770900182 13
1770900187 13
1770900192 13
```
</details>

---

