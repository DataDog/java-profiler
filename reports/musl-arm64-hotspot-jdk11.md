---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-23 12:28:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 11 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (2 unique values: 14-34 cores)</summary>

```
1792772663 14
1792772668 14
1792772673 14
1792772678 14
1792772683 14
1792772688 14
1792772693 34
1792772698 34
1792772703 34
1792772708 34
1792772713 34
1792772718 34
1792772723 34
1792772728 34
1792772733 34
1792772738 34
1792772743 34
1792772748 34
1792772753 34
1792772758 34
```
</details>

---

