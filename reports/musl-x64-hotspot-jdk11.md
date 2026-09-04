---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-04 09:37:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 782 |
| Sample Rate | 13.03/sec |
| Health Score | 814% |
| Threads | 11 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1788528773 92
1788528778 92
1788528783 92
1788528788 92
1788528793 92
1788528798 92
1788528803 92
1788528808 92
1788528813 94
1788528818 94
1788528823 96
1788528828 96
1788528833 96
1788528838 96
1788528843 96
1788528848 96
1788528853 96
1788528858 96
1788528863 96
1788528868 96
```
</details>

---

