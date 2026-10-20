---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-20 06:11:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 8 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 714 |
| Sample Rate | 11.90/sec |
| Health Score | 744% |
| Threads | 9 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1792490658 32
1792490663 32
1792490668 32
1792490673 32
1792490678 32
1792490683 32
1792490688 32
1792490693 32
1792490698 32
1792490703 32
1792490708 32
1792490713 32
1792490718 32
1792490723 32
1792490728 32
1792490733 32
1792490738 32
1792490743 32
1792490748 32
1792490753 32
```
</details>

---

