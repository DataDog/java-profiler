---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 02:28:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 10 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (3 unique values: 24-34 cores)</summary>

```
1789712678 24
1789712683 24
1789712688 24
1789712693 24
1789712698 29
1789712703 29
1789712708 29
1789712713 29
1789712718 29
1789712723 29
1789712728 29
1789712733 29
1789712738 29
1789712743 29
1789712748 29
1789712754 29
1789712759 29
1789712764 29
1789712769 34
1789712774 34
```
</details>

---

