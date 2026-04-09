---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-09 11:18:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 402 |
| Sample Rate | 6.70/sec |
| Health Score | 419% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 9 |
| Allocations | 433 |

<details>
<summary>CPU Timeline (3 unique values: 20-24 cores)</summary>

```
1775747636 22
1775747641 22
1775747646 22
1775747651 22
1775747656 22
1775747661 22
1775747666 24
1775747671 24
1775747676 24
1775747681 24
1775747686 24
1775747691 24
1775747696 24
1775747701 24
1775747706 24
1775747711 24
1775747716 24
1775747721 24
1775747726 24
1775747731 24
```
</details>

---

