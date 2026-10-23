---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-23 12:28:39 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 791 |
| Sample Rate | 13.18/sec |
| Health Score | 824% |
| Threads | 9 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1792772692 30
1792772697 30
1792772702 30
1792772707 30
1792772712 30
1792772717 30
1792772722 30
1792772727 30
1792772732 30
1792772737 30
1792772742 32
1792772747 32
1792772752 30
1792772757 30
1792772762 30
1792772767 30
1792772772 30
1792772777 30
1792772782 30
1792772787 30
```
</details>

---

