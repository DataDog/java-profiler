---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-29 09:55:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 414 |
| Sample Rate | 6.90/sec |
| Health Score | 431% |
| Threads | 9 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 11 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (4 unique values: 41-48 cores)</summary>

```
1793281792 46
1793281797 46
1793281802 41
1793281807 41
1793281812 41
1793281817 41
1793281822 41
1793281827 41
1793281832 41
1793281837 41
1793281842 41
1793281847 41
1793281852 41
1793281857 43
1793281862 43
1793281868 48
1793281873 48
1793281878 48
1793281883 48
1793281888 48
```
</details>

---

