---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-03 21:22:24 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 10 |
| Allocations | 87 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 10 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777857128 64
1777857133 64
1777857138 64
1777857143 64
1777857148 64
1777857153 64
1777857158 64
1777857163 64
1777857168 64
1777857173 64
1777857178 64
1777857183 64
1777857188 64
1777857193 64
1777857198 64
1777857203 64
1777857208 64
1777857213 64
1777857218 64
1777857223 64
```
</details>

---

