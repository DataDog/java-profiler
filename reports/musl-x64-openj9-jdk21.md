---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-05 20:41:46 EST

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 602 |
| Sample Rate | 10.03/sec |
| Health Score | 627% |
| Threads | 11 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 948 |
| Sample Rate | 15.80/sec |
| Health Score | 988% |
| Threads | 13 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (2 unique values: 77-82 cores)</summary>

```
1770341752 82
1770341757 82
1770341762 82
1770341767 82
1770341772 82
1770341777 82
1770341782 82
1770341788 82
1770341793 82
1770341798 77
1770341803 77
1770341808 77
1770341813 77
1770341818 77
1770341823 77
1770341828 77
1770341833 77
1770341838 77
1770341843 77
1770341848 77
```
</details>

---

