---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-09 11:18:33 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 751 |
| Sample Rate | 12.52/sec |
| Health Score | 782% |
| Threads | 11 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (4 unique values: 55-64 cores)</summary>

```
1775747631 64
1775747636 64
1775747641 64
1775747646 64
1775747651 64
1775747656 60
1775747661 60
1775747666 60
1775747671 60
1775747676 60
1775747681 60
1775747686 55
1775747691 55
1775747696 55
1775747701 55
1775747706 55
1775747711 55
1775747716 60
1775747721 60
1775747726 60
```
</details>

---

