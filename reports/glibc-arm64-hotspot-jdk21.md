---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-30 07:31:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 11 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 7 |
| Allocations | 4 |

<details>
<summary>CPU Timeline (3 unique values: 40-48 cores)</summary>

```
1790767624 45
1790767629 45
1790767634 45
1790767639 45
1790767644 45
1790767649 45
1790767654 48
1790767659 48
1790767664 48
1790767669 48
1790767674 48
1790767679 48
1790767684 48
1790767689 48
1790767694 40
1790767699 40
1790767704 40
1790767709 40
1790767714 40
1790767719 40
```
</details>

---

