---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 09:34:16 EST

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 736 |
| Sample Rate | 12.27/sec |
| Health Score | 767% |
| Threads | 11 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (3 unique values: 80-96 cores)</summary>

```
1794580113 90
1794580118 90
1794580123 90
1794580128 90
1794580133 90
1794580138 90
1794580143 96
1794580148 96
1794580153 96
1794580158 96
1794580163 96
1794580168 96
1794580173 96
1794580178 96
1794580183 96
1794580188 96
1794580193 96
1794580198 96
1794580203 96
1794580208 96
```
</details>

---

