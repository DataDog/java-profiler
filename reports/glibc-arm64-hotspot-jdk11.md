---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-23 12:28:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 168 |
| Sample Rate | 2.80/sec |
| Health Score | 175% |
| Threads | 10 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 29 |
| Sample Rate | 0.48/sec |
| Health Score | 30% |
| Threads | 11 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792772653 48
1792772658 48
1792772663 48
1792772668 48
1792772673 48
1792772678 48
1792772683 48
1792772689 48
1792772694 48
1792772699 48
1792772704 48
1792772709 48
1792772714 48
1792772719 48
1792772724 48
1792772729 48
1792772734 48
1792772739 43
1792772744 43
1792772749 43
```
</details>

---

